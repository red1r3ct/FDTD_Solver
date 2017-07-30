import React from 'react';
import PropTypes from 'prop-types';
import CenteredLayout from '../../components/CenteredLayout/CenteredLayout';
import Background from '../../components/Background/Background';
import Header from '../../components/Header/Header';
import AuthForm from '../../components/AuthForm/AuthForm';

export const Auth = ({ onLogin }) => (
	<Background>
		<Header/>
		<CenteredLayout>
			<AuthForm onLogin={onLogin}/>
		</CenteredLayout>
	</Background>
);

Auth.propTypes = {
	onLogin: PropTypes.func.isRequired,
};



export default Auth;
